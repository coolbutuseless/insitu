
test_that("br_cumsum() work", {
  
  set.seed(1)
  N <- 1000
  x0 <- runif(N)
  x1 <- duplicate(x0)
  
  br_cumsum(x1)
  expect_equal(x1, cumsum(x0))
})


test_that("br_cumprod() work", {
  
  set.seed(1)
  N <- 1000
  x0 <- runif(N)
  x1 <- duplicate(x0)
  
  br_cumprod(x1)
  expect_equal(x1, cumprod(x0))
})


test_that("br_cummax() work", {
  
  set.seed(1)
  N <- 1000
  x0 <- runif(N)
  x1 <- duplicate(x0)
  
  br_cummax(x1)
  expect_equal(x1, cummax(x0))
})


test_that("br_cummin() work", {
  
  set.seed(1)
  N <- 1000
  x0 <- runif(N)
  x1 <- duplicate(x0)
  
  br_cummin(x1)
  expect_equal(x1, cummin(x0))
})
