import Distribution.Simple.PackageIndex (SearchResult(None))
-- task 1 --

mult :: [Int] -> Int
mult x = foldl (*) 1 x
result1 = mult [5, 7, 8, 2]

-- task 2 --
posList :: [Int] -> [Int]
posList x = filter (>0) x
result2 = posList [-1, 5, 6, 7, -4, 0, 2 , -3]

-- task 3 --
trueList :: [Bool] -> Bool
trueList x = filter (== False) x == []
result3 = trueList [True, True, False, True]
result4 = trueList [True, True, True]
result5 = trueList [False, False, False]

-- task 4 --
evenList :: [Int] -> Bool
evenList x = filter (\n -> n `mod` 2 /= 0) x == [] 
result6 = evenList [2, 4, 5, 6]
result7 = evenList [2, 4, 6]
result8 = evenList [3, 5, 7]

-- task 5 --
maxList :: Ord a => [a] -> a
maxList x = foldl1 max x
result9 = maxList [4, 9, 2, 1, 13, 7]

-- task 6 --
inRange :: Int -> Int -> [Int] -> [Int]
check :: Ord a => a -> a -> a -> Bool
check a b x = x >= a && x <= b
inRange a b x = filter (check a b) x
result10 = inRange 3 7 [1, 2, 3, 4, 5, 6, 7, 8, 3]

-- task 7 --
countPositive :: [Int] -> Int
checkPos :: Int -> Int
checkPos x = if x > 0 then 1 else 0
countPositive x = foldl (+) 0 (map checkPos x)
result11 :: Int
result11 = countPositive [-1, 1, 2, 3, -2, 0]

-- task 8 --
myLength :: [a] -> Int
myLength x = foldl (+) 0 (map (const 1) x)
result12 = myLength "abcd"
