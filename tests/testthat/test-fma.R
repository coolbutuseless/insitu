
test_that("br_fmadd works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  br_fmadd(x, a, b)  
  expect_equal(x, xorig * a + b)
  
  # Scalar a
  x <- duplicate(xorig)
  br_fmadd(x, 2, b)  
  expect_equal(x, xorig * 2 + b)
  
  # Scalar b
  x <- duplicate(xorig)
  br_fmadd(x, a, 3)  
  expect_equal(x, xorig * a + 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  br_fmadd(x, 2, 3)  
  expect_equal(x, xorig * 2 + 3)
})



test_that("br_fmsub works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  br_fmsub(x, a, b)  
  expect_equal(x, xorig * a - b)
  
  # Scalar a
  x <- duplicate(xorig)
  br_fmsub(x, 2, b)  
  expect_equal(x, xorig * 2 - b)
  
  # Scalar b
  x <- duplicate(xorig)
  br_fmsub(x, a, 3)  
  expect_equal(x, xorig * a - 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  br_fmsub(x, 2, 3)  
  expect_equal(x, xorig * 2 - 3)
})



test_that("br_fnmadd works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  br_fnmadd(x, a, b)  
  expect_equal(x, -xorig * a + b)
  
  # Scalar a
  x <- duplicate(xorig)
  br_fnmadd(x, 2, b)  
  expect_equal(x, -xorig * 2 + b)
  
  # Scalar b
  x <- duplicate(xorig)
  br_fnmadd(x, a, 3)  
  expect_equal(x, -xorig * a + 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  br_fnmadd(x, 2, 3)  
  expect_equal(x, -xorig * 2 + 3)
})



test_that("br_fnmsub works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  br_fnmsub(x, a, b)  
  expect_equal(x, -xorig * a - b)
  
  # Scalar a
  x <- duplicate(xorig)
  br_fnmsub(x, 2, b)  
  expect_equal(x, -xorig * 2 - b)
  
  # Scalar b
  x <- duplicate(xorig)
  br_fnmsub(x, a, 3)  
  expect_equal(x, -xorig * a - 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  br_fnmsub(x, 2, 3)  
  expect_equal(x, -xorig * 2 - 3)
})

