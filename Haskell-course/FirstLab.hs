import Data.Char (toUpper, toLower)


x :: Int
x = 10

square :: Int -> Int
square x = x * x

pyth :: Int -> Int -> Int
pyth x y = square x + square y

isTriple :: Int -> Int -> Int -> Bool
isTriple x y z = pyth x y == square z

isTripleAny :: Int -> Int -> Int -> Bool
isTripleAny x y z = isTriple x y z || isTriple x z y || isTriple y x z || isTriple y z x || isTriple z x y || isTriple z y x


arr1 = [1, 2, 3, 4, 5, 6]
arr2 = [2, 4, 5, 6, 7, 8]

halfEvens :: [Int] -> [Int]
funcHalfE :: Int -> Int
funcHalfE x = if (x `mod` 2 == 0 ) then x `div` 2 else x
halfEvens x = map funcHalfE x
result1 = halfEvens arr1
result2 = halfEvens arr2

inRange :: Int -> Int -> [Int] -> [Int]
response_list = []
passedCheck :: Int -> Int -> Int -> Bool
passedCheck start end x = start <= x && x <= end
inRange start end list = [x | x <- list, passedCheck start end x]
result3 = inRange 2 6 [1..15]

countPositives :: [Int] -> Int
countPositives x = if (length x > 0) then if (head x > 0) then (1 + countPositives (tail x)) else (0 + countPositives (tail x)) else 0
result4 = countPositives [0,1,-3,-2,8,-1,6]

capitalised :: String -> String
capitalised x = toUpper (head x) : [(toLower y) | y <- (tail x)]
result5 = capitalised "lOWerS"

title :: [String] -> [String]
title x = [capitalised y | y <- x]
result6 = title ["tHe", "bOSun", "ANd", "thE", "BriDGe"]