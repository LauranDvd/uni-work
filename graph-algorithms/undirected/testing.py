def mask_to_str(numbers, mask):
    print("The following numbers were chosen:")
    n = len(numbers)
    for i in range(n):
        if mask & (1 << i):
            print(numbers[i])


def count_ways_to_obtain_subsum(numbers: list, how_many_numbers, given_sum):
    """
    Given a list of integers, counts in how many ways a given sum can be obtained using a given
    amount of numbers
    """

    n = len(numbers)
    count = 0
    for mask in range(0, 1 << n):
        subsum = 0
        how_many_ones = 0
        for i in range(0, n):
            if mask & (1 << i):
                subsum += numbers[i]
                how_many_ones += 1
        if subsum == given_sum and how_many_ones == how_many_numbers:
            mask_to_str(numbers, mask)
            count += 1

    return count


# generates all subgraphs with n-1 edges that have total cost 1
edges_costs = [2, 3, -1, 1, 4, 5, -3, -1, 2]
print(count_ways_to_obtain_subsum(edges_costs, 5, 1))
