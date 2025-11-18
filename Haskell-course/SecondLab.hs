import Data.Char

-- Task 1 --
-- 1 --
inRange :: Int -> Int -> [Int] -> [Int]
passedCheck :: Int -> Int -> Int -> Bool
passedCheck start end x = start <= x && x <= end
inRange start end [] = []
inRange start end list = if passedCheck start end (head list) then (head list) : (inRange start end (tail list)) else inRange start end (tail list)
result1 = inRange 2 6 [1..15]
-- 2 --
countPositives :: [Int] -> Int
countPositives x = if (length x > 0) then if (head x > 0) then (1 + countPositives (tail x)) else (0 + countPositives (tail x)) else 0
result2 = countPositives [0,1,-3,-2,8,-1,6]


-- Task 2 --
isort :: Ord a => [a] -> [a]
insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x list = if (head list) >= x then x : list else (head list) : insert x (tail list)
isort [] = []
isort x = insert (head x) (isort (tail x))

result3 = isort [1, 3, 4, 2, 5]

-- Task 3 --
-- merge [2,5,6] [1,3,4] produces [1,2,3,4,5,6] --
merge :: Ord a => [a] -> [a] -> [a] 
merge [] list2 = list2
merge list1 list2 = merge (tail list1) (isort ((head list1) : list2))

result4 = merge [2,5,6] [1,3,4]

-- Task 4 -- 
rotor :: Int -> String -> String
rotor number list 
    | number < 0 || number >= (length list) = "Error"
    | otherwise = addToBack number list
    where 
        addToBack 0 list = list
        addToBack number list = addToBack (number - 1) ((tail list) ++ [head list])

result5 = rotor 6 "ABCDEFGHIJKLMN"