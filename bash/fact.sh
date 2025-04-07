echo "enter a number  : "
read num

if [ "$num" -lt 0 ] ; then  
    echo "Enter a positive number"
    exit 1
fi

sum=1
for ((i=1;i<=num;i++))
do
    sum=$((sum*i))

done

echo "the fact is $sum"