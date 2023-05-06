def find_primes(n):
    """
    该函数接受一个整数 n，返回一个列表，其中包含 2 到 n 之间的所有质数
    """
    # 将2添加到质数列表中
    primes = [2]
    # 对于每个奇数，检查它是否是质数
    for num in range(3, n+1, 2):
        # 如果该数字可以被 2 到该数的平方根 之间的任何一个奇数整除，则它不是质数
        for i in range(3, int(num**0.5)+1, 2):
            if (num % i) == 0:
                break
        else:
            primes.append(num)
    return primes

# 找出1000以内的所有质数并打印
print(find_primes(1000))
