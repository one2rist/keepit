touch temp.txt
printf " " > temp.txt

#there are 520 000 unique english words, so lest take a million here:
for i in {1..1000000}
do
    printf "$i " >> temp.txt
done

touch test.txt
printf " " > test.txt

#copy and paste for the file to grow to ~32G:
for i in {1..4600}
do
    printf " " >> test.txt
    cat temp.txt >> test.txt
done

rm temp.txt
