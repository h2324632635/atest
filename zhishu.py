def find_primes(n):
    """
    该函数接受一个整数 n，返回一个列表，其中包含 2 到 n 之间的所有质数
    """
    primes = []
    for num in range(2, n+1):
        # 如果该数字可以被 2 到该数-1 之间的任何一个数字整除，则它不是质数
        for i in range(2, num):
            if (num % i) == 0:
                break
        else:
            primes.append(num)
    return primes

# 找出1000以内的所有质数并打印
print(find_primes(1000))
