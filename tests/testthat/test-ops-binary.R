


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Scalar
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + S works", {
  M <- matrix(1, 3, 2)
  s <- 1
  
  br_add(M, s)
  expect_equal(
    M,
    matrix(c(2, 2, 2,  2, 2, 2), 3, 2)
  )
})



test_that("add M + S with 'idx' works", {
  M <- matrix(1, 3, 2)
  s <- c(1)
  
  br_add(M, s, idx = c(1, 6))
  expect_equal(
    M,
    matrix(c(2, 1, 1,  1, 1, 2), 3, 2)
  )
})



test_that("add M + S with 'where' works", {
  M <- matrix(1, 3, 2)
  s <- c(1)
  
  br_add(M, s, where = c(T, F, F,  F, T, T))
  expect_equal(
    M,
    matrix(c(2, 1, 1,  1, 2, 2), 3, 2)
  )
})


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + V works", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v)
  expect_equal(
    M,
    matrix(c(2, 3, 4, 2, 3, 4), 3, 2)
  )
})



test_that("add M + V with 'idx' works", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, idx = c(1, 2))
  expect_equal(
    M,
    matrix(c(2, 3, 1, 2, 3, 1), 3, 2)
  )
})



test_that("add M + V with 'where' works", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, where = c(T, F, F))
  expect_equal(
    M,
    matrix(c(2, 1, 1,  2, 1, 1), 3, 2)
  )
})


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Matrix
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + N works", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N)
  expect_equal(
    M,
    matrix(c(3, 3, 3,  3, 3, 3), 3, 2)
  )
})



test_that("add M + V with 'idx' works", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, idx = c(1, 6))
  expect_equal(
    M,
    matrix(c(3, 1, 1,  1, 1, 3), 3, 2)
  )
})



test_that("add M + N with 'where' works", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, where = c(T, F, F,  F, T, T))
  expect_equal(
    M,
    matrix(c(3, 1, 1,  1, 3, 3), 3, 2)
  )
})



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Scalar  -  with cols = VECTOR
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + S works with 'cols'", {
  M <- matrix(1, 3, 2)
  s <- 1
  
  br_add(M, s, cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  2, 2, 2), 3, 2)
  )
})



test_that("add M + S with 'idx' works with 'cols'", {
  M <- matrix(1, 3, 2)
  s <- c(1)

  # Index must refer to within-column location
  expect_error(  
    br_add(M, s, idx = c(1, 6), cols = 2)
  )
  
  br_add(M, s, idx = c(1, 3), cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  2, 1, 2), 3, 2)
  )
})



test_that("add M + S with 'where' works with 'cols'", {
  M <- matrix(1, 3, 2)
  s <- c(1)
  
  # Since 'cols' is specified, 'where' must be within-column index
  expect_error(
    br_add(M, s, where = c(T, F, F,  F, T, T), cols = 2)
  )
  
  br_add(M, s, where = c(T, T, F), cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  2, 2, 1), 3, 2)
  )
})





#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Vector with cols = VECTOR
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + V works with 'cols'", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1, 2, 3, 4), 3, 2)
  )
})



test_that("add M + V with 'idx' works with 'cols'", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, idx = c(1, 2), cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  2, 3, 1), 3, 2)
  )
})



test_that("add M + V with 'where' works with 'cols'", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, where = c(T, F, F), cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  2, 1, 1), 3, 2)
  )
})




#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Matrix with cols = VECTOR
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + N works with 'cols'", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  3, 3, 3), 3, 2)
  )
})



test_that("add M + N with 'idx' works with 'cols'", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, idx = c(1, 3), cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  3, 1, 3), 3, 2)
  )
})



test_that("add M + N with 'where' works with 'cols'", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, where = c(F, T, T), cols = 2)
  expect_equal(
    M,
    matrix(c(1, 1, 1,  1, 3, 3), 3, 2)
  )
})





#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Scalar  -  with cols = NA
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + S works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  s <- 1
  
  br_add(M, s, cols = NA)
  expect_equal(
    M,
    matrix(c(2, 2, 2,  2, 2, 2), 3, 2)
  )
})



test_that("add M + S with 'idx' works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  s <- c(1)
  
  # Index must refer to within-column location
  expect_error(  
    br_add(M, s, idx = c(1, 6), cols = 2)
  )
  
  br_add(M, s, idx = c(1, 3), cols = NA)
  expect_equal(
    M,
    matrix(c(2, 1, 2,  2, 1, 2), 3, 2)
  )
})



test_that("add M + S with 'where' works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  s <- c(1)
  
  # Since 'cols' is specified, 'where' must be within-column index
  expect_error(
    br_add(M, s, where = c(T, F, F,  F, T, T), cols = 2)
  )
  
  br_add(M, s, where = c(T, T, F), cols = NA)
  expect_equal(
    M,
    matrix(c(2, 2, 1,  2, 2, 1), 3, 2)
  )
})





#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Vector with cols = NA
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + V works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, cols = NA)
  expect_equal(
    M,
    matrix(c(2, 3, 4,  2, 3, 4), 3, 2)
  )
})



test_that("add M + V with 'idx' works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, idx = c(1, 2), cols = NA)
  expect_equal(
    M,
    matrix(c(2, 3, 1,  2, 3, 1), 3, 2)
  )
})



test_that("add M + V with 'where' works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  v <- c(1, 2, 3)
  
  br_add(M, v, where = c(T, F, F), cols = NA)
  expect_equal(
    M,
    matrix(c(2, 1, 1,  2, 1, 1), 3, 2)
  )
})




#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Matrix : Matrix with cols = NA
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("add M + N works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, cols = NA)
  expect_equal(
    M,
    matrix(c(3, 3, 3,  3, 3, 3), 3, 2)
  )
})



test_that("add M + N with 'idx' works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, idx = c(1, 3), cols = NA)
  expect_equal(
    M,
    matrix(c(3, 1, 3,  3, 1, 3), 3, 2)
  )
})



test_that("add M + N with 'where' works with 'cols' = NA", {
  M <- matrix(1, 3, 2)
  N <- matrix(2, 3, 2)
  
  br_add(M, N, where = c(F, T, T), cols = NA)
  expect_equal(
    M,
    matrix(c(1, 3, 3,  1, 3, 3), 3, 2)
  )
})



