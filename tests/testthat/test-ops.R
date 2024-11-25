
test_that("ops plus workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_add(x, y), xorig + y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_add(x, 2), xorig + 2)
})


test_that("ops minus workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_sub(x, y), xorig - y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_sub(x, 2), xorig - 2)
})


test_that("ops mult workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_mul(x, y), xorig * y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_mul(x, 2), xorig * 2)
})



test_that("ops divide workds", {
  
  # setup
  set.seed(1)
  N <- 10
  xorig  <- as.numeric(seq_len(N))
  y <- runif(N)
  
  # vector y
  x <- duplicate(xorig)
  expect_equal(ins_div(x, y), xorig / y)
  
  # scalar y
  x <- duplicate(xorig)
  expect_equal(ins_div(x, 2), xorig / 2)
})
