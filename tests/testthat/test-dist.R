
test_that("br_mat_dist3 works", {

  set.seed(1)
  N <- 10
  mat1 <- matrix(runif(3 * N), N, 3)
  mat2 <- matrix(runif(3 * N), N, 3)
  d1 <- alloc_n(N)
  
  
  d2 <- sqrt(rowSums((mat2 - mat1)^2))
  d2
  
  br_mat_dist3(d1, mat1, mat2)
  d1

  
  expect_equal(d1, d2)
  
})



test_that("br_mat_dist2 works", {
  
  set.seed(1)
  N <- 10
  mat1 <- matrix(runif(2 * N), N, 2)
  mat2 <- matrix(runif(2 * N), N, 2)
  d1 <- alloc_n(N)
  
  
  d2 <- sqrt(rowSums((mat2 - mat1)^2))
  d2
  
  br_mat_dist2(d1, mat1, mat2)
  d1
  
  
  expect_equal(d1, d2)
  
})