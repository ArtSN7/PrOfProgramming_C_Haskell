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
-------------------------------------------

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


-- Task 3 --

trib :: Integral a => a -> a
trib 1 = 0
trib 2 = 0
trib 3 = 1
trib n = trib (n-1) + trib (n-2) + trib (n-3)

trib2 :: Integral a => a -> a
trib2 n = compute n 0 0 1
  where
    compute num a b c
      | num == 1    = a
      | num == 2    = b
      | num == 3    = c
      | otherwise = compute (num-1) b c (a + b + c)


{--

C-implementation:
-----------------

long long trib2(long long n) {

    long long a = 0;
    long long b = 0;
    long long c = 1;

    if (n == 1) return a;
    if (n == 2) return b;
    if (n == 3) return c;

    long long num = n;

    while (num > 3) {

        long long next = a + b + c;
        a = b;
        b = c;
        c = next;
        num = num - 1;

    }

    return c;
}

--}


{--

Pre-condition for trib:

    Input n is an integer where n ≥ 1

Post-condition for trib:

    The result is the n‑th Tribonacci number in the sequence 0, 0, 1, 1, 2, 4, 7, ... that satisfies the next:
    
    {
    |    T(1) = 0, T(2) = 0, T(3) = 1
    |    T(n) = T(n-1) + T(n-2) + T(n-3) for all n ≥ 4
    }

--}


{--

Correctness proof for trib:
---------------------------

For all n ≥ 1, trib n = T(n)

Base cases:

    n = 1: trib 1 = 0 = T(1) 
    n = 2: trib 2 = 0 = T(2) 
    n = 3: trib 3 = 1 = T(3) 

Assume that for some num >= 3:

    trib (k-2) = T(k-2)
    trib (k-1) = T(k-1)
    trib k = T(k)

Then prove for n = k + 1:

    trib (k+1) = trib k + trib (k-1) + trib (k-2)   - by def of trib
           = T(k) + T(k-1) + T(k-2)                 - by assumptions
           = T(k+1)                                 - by def of T

Hence, as it is true for n = 1, 2, 3 and it was shown to be true for n = k + 1, hence it can be proven by MMI that treb is correct

--}


{--

Correctness proof for trib2 and compute:
---------------------------

For all n ≥ 1 and j ≥ 0, 1, 2, if we call
    
    compute n (T(j)) (T(j+1)) (T(j+2))

then compute returns 

    T(n+j)

Pre-condition: 
    n ≥ 1, a = T(j), b = T(j+1), c = T(j+2) for some j

Post-condition: 
    compute n a b c = T(n+j)



Proof by induction on n:

    Base case:

        n = 1: compute 1 a b c = a = T(j) = T(1+j) 
        n = 2: compute 2 a b c = b = T(j+1) = T(2+j) 
        n = 3: compute 3 a b c = c = T(j+2) = T(3+j) 

    Inductive step:

        Assume the invariant holds for n = k ≥ 3

        Prove for n = k+1:

            compute (k+1) (T(j)) (T(j+1)) (T(j+2))
            = compute k (T(j+1)) (T(j+2)) (T(j) + T(j+1) + T(j+2))              -  by def, since k+1 > 3
            = compute k (T(j+1)) (T(j+2)) (T(j+3))                              -  by Tribonacci recurrence
            = T(k + (j+1))                                                      -  by induction hypothesis with j replaced by j+1
            = T((k+1) + j)  
        
        Hence the invariant holds for all n ≥ 1


Proof foir trib2:

    For all n ≥ 1, trib2 n = T(n), to prove:

        trib2 n = compute n 0 0 1           - by def of trib2
        = compute n (T(1)) (T(2)) (T(3))    - since T(1)=0, T(2)=0, T(3)=1 
        = T(n + 0)                          - by Part 2 invariant with j=0 
        = T(n)  

    Hence, trib2 is correct

--}



    