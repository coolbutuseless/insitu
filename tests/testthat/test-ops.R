
test_that("ops plus workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_plus(x, y), xorig + y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_plus(x, 2), xorig + 2)
})


test_that("ops minus workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_minus(x, y), xorig - y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_minus(x, 2), xorig - 2)
})


test_that("ops mult workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_mult(x, y), xorig * y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_mult(x, 2), xorig * 2)
})



test_that("ops divide workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_divide(x, y), xorig / y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_divide(x, 2), xorig / 2)
})
