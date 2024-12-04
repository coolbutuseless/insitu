

k <- 20

test_that("matrix vector multiply works", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  x <- runif(1 * k)
  
  y1 <- A %*% x
  
  y2 <- numeric(2 * k)
  br_mat_vec_mul(y2, A, x)
  
  expect_equal(as.vector(y1), y2)
})



test_that("matrix vector multiply works with alpha", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  x <- runif(1 * k)
  
  alpha <- 1.23
  y1 <- alpha * (A %*% x)
  
  y2 <- numeric(2 * k)
  br_mat_vec_mul(y2, A, x, alpha = alpha)
  
  expect_equal(as.vector(y1), y2)
})


