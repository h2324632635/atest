def sieve_of_eratosthenes(n):
    """
    该函数接受一个整数 n，返回一个列表，其中包含 2 到 n 之间的所有质数
    """
    # 初始化列表，所有数默认为质数
    primes = [True] * (n + 1)
    # 0和1不是质数，因此将它们标记为False
    primes[0] = primes[1] = False

    # 从2开始，直到n的平方根，标记所有的合数
    for i in range(2, int(n**0.5)+1):
        if primes[i]:
            # 将i的所有倍数标记为False
            for j in range(i**2, n+1, i):
                primes[j] = False
    
    # 找出所有的质数
    return [num for num, is_prime in enumerate(primes) if is_prime]

# 找出100000以内的所有质数并打印前10个
primes = sieve_of_eratosthenes(100000)
print(primes[:10])
