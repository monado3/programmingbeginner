print("半角数字をスペース区切りで入力してください")
#ECCSのmacのターミナルから実行する際は上の文をコメントアウトしないと実行できない

original=list(map(int,input().rstrip().split()))
leng=len(original)
flag=0
while flag!=1:
    flag=1
    for i in range(leng-1):
        if original[i]>original[i+1]:
            original[i],original[i+1]=original[i+1],original[i]
            flag=0
for i in original:
    print(i,end=" ")
print()