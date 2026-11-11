def has_pair_sum(nums: list[int], target: int) -> bool:
    start = 0
    end = len(nums) - 1
    while start < end:
        if nums[start] + nums[end] == target:
            return True
        if nums[start] + nums[end] < target:
            start += 1
        else:
            end -= 1
    return False
