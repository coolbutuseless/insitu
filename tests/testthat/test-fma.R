
test_that("fmadd works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  fmadd(x, a, b)  
  expect_equal(x, xorig * a + b)
  
  # Scalar a
  x <- duplicate(xorig)
  fmadd(x, 2, b)  
  expect_equal(x, xorig * 2 + b)
  
  # Scalar b
  x <- duplicate(xorig)
  fmadd(x, a, 3)  
  expect_equal(x, xorig * a + 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  fmadd(x, 2, 3)  
  expect_equal(x, xorig * 2 + 3)
})



test_that("fmsub works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  fmsub(x, a, b)  
  expect_equal(x, xorig * a - b)
  
  # Scalar a
  x <- duplicate(xorig)
  fmsub(x, 2, b)  
  expect_equal(x, xorig * 2 - b)
  
  # Scalar b
  x <- duplicate(xorig)
  fmsub(x, a, 3)  
  expect_equal(x, xorig * a - 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  fmsub(x, 2, 3)  
  expect_equal(x, xorig * 2 - 3)
})



test_that("fnmadd works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  fnmadd(x, a, b)  
  expect_equal(x, -xorig * a + b)
  
  # Scalar a
  x <- duplicate(xorig)
  fnmadd(x, 2, b)  
  expect_equal(x, -xorig * 2 + b)
  
  # Scalar b
  x <- duplicate(xorig)
  fnmadd(x, a, 3)  
  expect_equal(x, -xorig * a + 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  fnmadd(x, 2, 3)  
  expect_equal(x, -xorig * 2 + 3)
})



test_that("fnmsub works", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  
  # vector x, a, b
  x <- duplicate(xorig)
  a <- runif(N)
  b <- runif(N)
  fnmsub(x, a, b)  
  expect_equal(x, -xorig * a - b)
  
  # Scalar a
  x <- duplicate(xorig)
  fnmsub(x, 2, b)  
  expect_equal(x, -xorig * 2 - b)
  
  # Scalar b
  x <- duplicate(xorig)
  fnmsub(x, a, 3)  
  expect_equal(x, -xorig * a - 3)
  
  # Scalar a, b
  x <- duplicate(xorig)
  fnmsub(x, 2, 3)  
  expect_equal(x, -xorig * 2 - 3)
})

