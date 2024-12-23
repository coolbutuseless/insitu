

test_that("mat-col-get works", {
  
  m <- matrix(as.numeric(1:6), 2, 3)
  v <- alloc_n(nrow(m))
  br_mat_col_get(m, 2, v)
  expect_identical(v, m[,2])
  
})



test_that("mat-col-set works", {
  
  m <- matrix(as.numeric(1:6), 2, 3)
  v <- c(9, 9)
  br_mat_col_set(m, 2, v)
  expect_identical(m, matrix(c(1, 2, 9, 9, 5, 6), 2, 3))
  
  
  m <- matrix(as.numeric(1:6), 2, 3)
  br_mat_col_set(m, 2, 8)
  expect_identical(m, matrix(c(1, 2, 8, 8, 5, 6), 2, 3))
  
})



test_that("mat-row-get works", {
  
  m <- matrix(as.numeric(1:6), 2, 3)
  v <- alloc_n(ncol(m))
  br_mat_row_get(m, 2, v)
  expect_identical(v, m[2,])
  
})




test_that("mat-row-set works", {
  
  m <- matrix(as.numeric(1:6), 2, 3)
  v <- c(9, 9, 9)
  br_mat_row_set(m, 2, v)
  expect_identical(m, matrix(c(1, 9, 3, 9, 5, 9), 2, 3))
  
  m <- matrix(as.numeric(1:6), 2, 3)
  br_mat_row_set(m, 2, 7)
  expect_identical(m, matrix(c(1, 7, 3, 7, 5, 7), 2, 3))
  
})