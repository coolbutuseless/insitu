

k <- 20

test_that("matrix vector multiply works", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  x <- runif(1 * k)
  
  y1 <- A %*% x
  
  y2 <- numeric(2 * k)
  br_mat_vec_mul(y2, A, x)
  
  expect_equal(y2, as.vector(y1))
})



test_that("matrix vector multiply works with alpha", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  x <- runif(1 * k)
  
  alpha <- 1.23
  y1 <- alpha * (A %*% x)
  
  y2 <- numeric(2 * k)
  br_mat_vec_mul(y2, A, x, alpha = alpha)
  
  expect_equal(y2, as.vector(y1))
})




test_that("matrix vector multiply works with t(A)", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 1*k, 2*k)
  x <- runif(1 * k)
  
  y1 <- t(A) %*% x
  
  y2 <- numeric(2 * k)
  br_mat_vec_mul(y2, A, x, ta = TRUE)
  
  y1
  y2
  
  expect_equal(y2, as.vector(y1))
})





test_that("matrix vector multiply works with A square", {
  
  set.seed(1)
  A <- matrix(runif(1 * k * k), 1*k, 1*k)
  x <- runif(1 * k)
  
  y1 <- A %*% x
  
  br_mat_vec_mul_asq(A, x)
  
  expect_equal(x, as.vector(y1))
})
