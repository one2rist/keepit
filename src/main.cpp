#include "fileReader.h"
#include "functions.h"

#include <utility>
#include <set>
#include <unordered_set>
#include <list>

#include <future>


using namespace std::literals;
using WordContainer = std::unordered_set<std::string>;
using TaskHandle = std::future<WordContainer>;
using Tasks = std::list<TaskHandle>;

constexpr std::streamsize BUFFSIZE = 100*1024*1024; // TODO change interfaces to have this parameter dynamic, based on file size. The current one is good for 32gb file end 6cores/8GiB/Ubuntu. 
constexpr size_t PROCESSES = 12;                    // TODO see above. The current is the machine's cores * 2
constexpr size_t READY_GAIN = 2;                    // Must be 2+. 2 looks reasonable, + tested.
constexpr auto TIMEOUT = 50ms;                      // 50 ms looks reasonable

void run(const std::string& fileName) {
    FileReader fileReader(fileName, BUFFSIZE);
    Tasks tasks;
    Tasks tasks_ready;

    // looping until there is data in the file
    // or async tasks to check the result:
    // or at least 2 ready task to merge their results
    while (fileReader.good() or !tasks.empty() or tasks_ready.size() > 1) {

        // start (no more than PROCESSES) tasks:
        while (tasks.size() < PROCESSES and fileReader.good()) {
            // ASYNC TASK: SPLIT STRING TO WORDS
            // INPUT: string read from file
            // RESULT: container of words
            tasks.emplace_back(
                    std::async(
                        std::launch::async,
                        [](const auto& s) {
                            WordContainer result;
                            cmmn::split(result, s, ' ');
                            return result;
                        },
                        fileReader.read()
                        )
                    );

            cmmn::visualize_progress(':');
        }


        // check by timeout if there are ready tasks to get the result:
        // ready task goes to tasks_ready
        while (!tasks.empty() and tasks_ready.size() < READY_GAIN) {
            std::this_thread::sleep_for(TIMEOUT);
            auto i = tasks.begin();
            while (i != tasks.end()) {
                if ((*i).wait_for(0s) == std::future_status::ready) {
                    // relink ready-task from tasks to tasks_ready list:
                    tasks_ready.splice(tasks_ready.end(), tasks, i++);
                }
                ++i;
            }
        }

        // at this point we may have some free PROCESSES
        // and some data from the 'ready' tasks to proceed
        // if there are 2+ ready tasks, we can async merge the two results
        while (tasks_ready.size() > 1) {
            auto i = tasks_ready.begin();
            auto _1 = (*i).get();
            tasks_ready.erase(i++);
            auto _2 = (*i).get();
            tasks_ready.erase(i++);
            // ASYNC TASK: merge 2 containers of words
            // INPUT: 2 container of words
            // RESULT: container of words
            tasks.emplace_back(
                    std::async(
                        std::launch::async,
                        [_1=std::move(_1), _2=std::move(_2)]() mutable {
                            _1.merge(_2);
                            return _1;
                        }
                        )
                    );

            cmmn::visualize_progress('.');
        }
    }

    // the last task contains the final WordContainer:
    if (tasks_ready.size()==1) {
        std::cout << "\nThe number of unique words in the file: " << tasks_ready.back().get().size() << std::endl;
    } else { std::cout << "\nSomething went wrong"; }
}


int main()
try {
    run("input.txt");
    run("test_1m.txt");
    return 0;
} catch (const std::system_error& e) {
    std::cout << "[ERROR] : run out of threads.. " << e.what();
    return -1;
} catch (const std::bad_alloc& e) {
    std::cout << "[ERROR] : run out of memory .. " << e.what();
    return -2;
} catch (...) {
    std::cout << "[ERROR]: caught unhandled exception";
    return -3;
}
