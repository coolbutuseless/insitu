

test_that("hypot3 works", {
  
  # Distance from origin in 3D
  N <- 1000
  x <- rep(1, N)
  y <- rnorm(N)
  z <- rnorm(N)
  mat <- cbind(x, y, z)
  d1 <- alloc_n(N)
  br_mat_hypot3(d1, mat)
  d1
  
  # Compare to base R
  d2 <- sqrt(x * x + y * y + z * z)
  
  expect_equal(d1, d2)
  
})


test_that("hypot2 works", {
  
  # Distance from origin in 3D
  N <- 1000
  x <- rep(1, N)
  y <- rnorm(N)
  mat <- cbind(x, y)
  d1 <- alloc_n(N)
  br_mat_hypot2(d1, mat)
  d1
  
  # Compare to base R
  d2 <- sqrt(x * x + y * y)
  
  expect_equal(d1, d2)
  
})
