-- task 1 --
ns :: [Int] -> [Int]
ns x = map (^2) x

sum_of_ns :: [Int] -> Int
sum_of_ns x = foldr1 (+) (ns x)

check_if_greater :: [Int] -> Char
check_if_greater x = if length(filter (<=0) x) > 0 then 'N' else 'Y'

-- task 2 --

task2 :: (Int -> Int) -> [Int] -> Int
f x = x * x
n = 5
task2 func x = minimum (map (func) x)

result2 = task2 f [0..n]

-- task 3 --
twice :: (a -> a) -> a -> a
twice f x = f(f(x))