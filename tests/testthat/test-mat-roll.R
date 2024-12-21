
test_that("mat-roll(0) works", {
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  mat0 <- duplicate(mat)
  
  br_mat_roll(mat)
  expect_equal(mat, mat0)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = 0, cols = 0)
  expect_equal(mat, mat0)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = 3, cols = 0)
  expect_equal(mat, mat0)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = 3, cols = 2)
  expect_equal(mat, mat0)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = 6, cols = 2)
  expect_equal(mat, mat0)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = -6, cols = -4)
  expect_equal(mat, mat0)
  
})





test_that("mat-roll(cols) works", {
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  mat0 <- duplicate(mat)
  mat1 <- matrix(c(4, 5, 6, 1, 2, 3), nrow = 3, ncol = 2)
  
  br_mat_roll(mat, cols = 1)
  expect_equal(mat, mat1)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, cols = -1)
  expect_equal(mat, mat1)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, cols = -4)
  expect_equal(mat, mat0)
})



test_that("mat-roll(rows) works", {
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  mat0 <- duplicate(mat)
  mat1 <- matrix(c(3, 1, 2, 6, 4, 5), nrow = 3, ncol = 2)
  mat2 <- matrix(c(2, 3, 1, 5, 6, 4), nrow = 3, ncol = 2)
  
  br_mat_roll(mat, rows = 1)
  expect_equal(mat, mat1)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = 2)
  expect_equal(mat, mat2)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = -1)
  expect_equal(mat, mat2)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = -2)
  expect_equal(mat, mat1)
})



test_that("mat-roll(rows, cols) works", {
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  mat0 <- duplicate(mat)
  mat11 <- matrix(c(6, 4, 5,  3, 1, 2), nrow = 3, ncol = 2)
  mat21 <- matrix(c(5, 6, 4,  2, 3, 1), nrow = 3, ncol = 2)
  
  br_mat_roll(mat, rows = 1, cols = 1)
  expect_equal(mat, mat11)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = 2, cols = 1)
  expect_equal(mat, mat21)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = -1, cols = 1)
  expect_equal(mat, mat21)
  
  mat <- matrix(as.numeric(1:6), nrow = 3, ncol = 2)
  br_mat_roll(mat, rows = -2, cols = -1)
  expect_equal(mat, mat11)
})














