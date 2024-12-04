

k <- 20

test_that("matrix vector multiply (asq) works", {
  
  set.seed(1)
  A <- matrix(runif(1 * k * k), 1*k, 1*k)
  x <- runif(1 * k)
  
  y1 <- A %*% x
  
  br_mat_vec_mul_asq(A, x)
  
  expect_equal(as.vector(y1), x)
})



test_that("matrix vector multiply (asq) works with alpha", {
  
  set.seed(1)
  A <- matrix(runif(1 * k * k), 1*k, 1*k)
  x <- runif(1 * k)
  
  alpha <- 1.23
  y1 <- alpha * (A %*% x)
  
  br_mat_vec_mul_asq(A, x, alpha = alpha)
  
  expect_equal(as.vector(y1), x)
})


