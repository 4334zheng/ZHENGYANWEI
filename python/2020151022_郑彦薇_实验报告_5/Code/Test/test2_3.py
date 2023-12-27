def twoSumClosest(nums, target):
    l = len(nums)
    min = 1000
    for i in range(1, l):
        for j in range(i+1, l):
            if (target-nums[i]-nums[j])<min :
                min = target-nums[i]-nums[j]
    return min

num = input("Enter the array: ")
nums = [int(n) for n in num.split()]
target = int(input("Enter the target: "))
print(twoSumClosest(nums, target))
