

k <- 20

test_that("matrix matrix multiply works", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  B <- matrix(runif(3 * k * k), 1*k, 3*k)
  
  C1 <- A %*% B
  
  C2 <- alloc_mat_mat_mul(A, B)
  br_mat_mat_mul(C2, A, B)
  
  expect_equal(C1, C2)
})



test_that("matrix matrix multiply works with alpha", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  B <- matrix(runif(3 * k * k), 1*k, 3*k)
  
  alpha <- 1.23
  C1 <- alpha * (A %*% B)
  
  C2 <- alloc_mat_mat_mul(A, B)
  br_mat_mat_mul(C2, A, B, alpha = alpha)
  
  expect_equal(C1, C2)
})



test_that("matrix matrix multiply works with t(A)", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 1*k, 2*k)
  B <- matrix(runif(3 * k * k), 1*k, 3*k)
  
  C1 <- t(A) %*% B
  
  C2 <- alloc_mat_mat_mul(A, B, ta = TRUE)
  br_mat_mat_mul(C2, A, B, ta = TRUE)
  expect_identical(dim(C1), dim(C2))
  
  expect_equal(C1, C2)
})


test_that("matrix matrix multiply works with t(B)", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 2*k, 1*k)
  B <- matrix(runif(3 * k * k), 3*k, 1*k)
  
  C1 <- A %*% t(B)
  
  C2 <- alloc_mat_mat_mul(A, B, tb = TRUE)
  br_mat_mat_mul(C2, A, B, tb = TRUE)
  expect_identical(dim(C1), dim(C2))
  
  expect_equal(C1, C2)
})


test_that("matrix matrix multiply works with t(A) and t(B)", {
  
  set.seed(1)
  A <- matrix(runif(2 * k * k), 1*k, 2*k)
  B <- matrix(runif(3 * k * k), 3*k, 1*k)
  
  C1 <- t(A) %*% t(B)
  
  C2 <- alloc_mat_mat_mul(A, B, ta = TRUE, tb = TRUE)
  br_mat_mat_mul(C2, A, B, ta = TRUE, tb = TRUE)
  expect_identical(dim(C1), dim(C2))
  
  expect_equal(C1, C2)
})
