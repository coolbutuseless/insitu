
k <- 20

test_that("matrix matrix multiply (bsq) works", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  B <- matrix(runif(1 * k * k), 1*k, 1*k)
  
  C1 <- A %*% B
  
  br_mat_mat_mul_bsq(A, B)
  
  expect_equal(C1, A)
})



test_that("matrix matrix multiply (bsq) works with alpha", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  B <- matrix(runif(1 * k * k), 1*k, 1*k)
  
  alpha <- 1.23
  C1 <- alpha * (A %*% B)
  
  br_mat_mat_mul_bsq(A, B, alpha = alpha)
  
  expect_equal(C1, A)
})

