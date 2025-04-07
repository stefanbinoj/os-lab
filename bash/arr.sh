echo "enter length"
read n

num=()
for ((i=0;i<n;i++))
do
    echo "enter"
    read a
    num[i]=$a
done

sum=0
for ((i=0;i<n;i++))
do
    sum=$((sum+${num[i]}))
done

echo "sum is $sum"