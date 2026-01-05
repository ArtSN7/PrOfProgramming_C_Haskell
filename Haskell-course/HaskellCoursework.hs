-- Task 1 --

printNTimes :: Int -> IO ()
printNTimes n
  | n <= 0    = return ()
  | otherwise = do
      putStrLn "I love Haskell!"
      printNTimes (n - 1)

foolCheck :: IO Int
foolCheck = do
    putStrLn "Input a whole number: "
    line <- getLine
    let number = read line :: Int
    if number <= 0
      then do
        putStrLn "Positive number must be entered. Please try again."
        foolCheck
      else return number


iLoveHaskell :: IO()
iLoveHaskell = do
    number <- foolCheck
    printNTimes number


-- Task 2 --

data STree = Leaf String | Node (STree) String (STree) deriving Show
tDepth :: STree -> Int
tDepth (Leaf _) = 1
tDepth (Node left _ right) = 1 + max (tDepth left) (tDepth right)

tMirror :: STree -> STree
tMirror (Leaf value) = Leaf value
tMirror (Node left value right) = Node (tMirror right) value (tMirror left)

{-- 

Proof by induction ( A-Level FM template ):
-------------------

Prove that 'tDepth (tMirror T) = tDepth T' is true for every T, where T is of STree type

Base case:

    T = Leaf s , hence

    tDepth (Leaf s) = 1
    tDepth (tMirror (Leaf s)) = 1 
    
    => both sides are equal to 1

General case:

    For t = Node l v r , tDepth (Node l v r) = tDepth (tMirror (Node l v r))

    Assume that if 
        
        t = Node l v r 
    
    then 

        tDepth (tMirror l) = tDepth l
        tDepth (tMirror r) = tDepth r

    So, prove for 
        
        tDepth (tMirror (Node l v r)) =>

        tDepth (tMirror (Node l v r)) = tDepth (Node (tMirror r) v (tMirror l)) - by def of tMirror =>

        tDepth (Node (tMirror r) v (tMirror l)) = 1 + max (tDepth (tMirror r)) (tDepth (tMirror l)) - by def of tDepth =>

        1 + max (tDepth (tMirror r)) (tDepth (tMirror l)) = 1 + max (tDepth r) (tDepth l) - based on the assumption =>

        1 + max (tDepth r) (tDepth l) = 1 + max (tDepth l) (tDepth r) - based on the commutative properties =>

        1 + max (tDepth l) (tDepth r) = tDepth (Node l v r)


    All in all, as it is true for T = Leaf s, and it was shown to be true T = Node l v r under assumption that tDepth (tMirror l) = tDepth l and tDepth (tMirror r) = tDepth r,
    hence it can be proven by method of mathematical induction that tDepth (tMirror T) = tDepth T' is true for every T, where T is of STree type
    
--}