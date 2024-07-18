
print('Starting program...')

n = int(input())
arr = []
for i in range(n):
    arr.append(int(input()))

sum = 0
for i in range(n):
    sum += arr[i]

print("Sum of array elements = ", sum)

print("\n________End of Program_________")