
test_that("matrix unary sqrt works", {
  A0 <- matrix(as.numeric(1:6), 3, 2)
  A1 <- duplicate(A0)
  
  ybr_sqrt(A1)
  
  expect_identical(
    A1,
    sqrt(A0)
  )
})



# test_that("matrix unary sqrt with idx works", {
#   A0 <- matrix(as.numeric(1:6), 3, 2)
#   A1 <- duplicate(A0)
#   
#   ybr_sqrt(A1, idx = c(1, 6))
#   
#   A0[1] <- sqrt(A0[1])
#   A0[6] <- sqrt(A0[6])
#   
#   expect_identical(
#     A1,
#     A0
#   )
# })



test_that("matrix unary sqrt with 'where' works", {
  A0 <- matrix(as.numeric(1:6), 3, 2)
  A1 <- duplicate(A0)
  
  ybr_sqrt(A1, where = c(F, F, F, F, T, T))
  
  A0[5] <- sqrt(A0[5])
  A0[6] <- sqrt(A0[6])
  
  expect_identical(
    A1,
    A0
  )
})



test_that("matrix unary sqrt with 'where' of incorrect length fails", {
  A0 <- matrix(as.numeric(1:6), 3, 2)
  
  expect_error(
    ybr_sqrt(A0, where = c(F, F, F, T)),
    "Length mismatch: "
  )
})


test_that("matrix unary sqrt with 'idx' out-of-bounds fails", {
  A0 <- matrix(as.numeric(1:6), 3, 2)
  
  expect_error(
    ybr_sqrt(A0, idx = c(7)),
    "out-of-bounds"
  )
})


test_that("matrix unary sqrt with length(where) == nrow(matrix) works", {
  A0 <- matrix(as.numeric(1:6), 3, 2)
  A1 <- duplicate(A0)
  
  ybr_sqrt(A1, where = c(F, T, F))
  
  A0[2] <- sqrt(A0[2])
  A0[5] <- sqrt(A0[5])
  
  expect_identical(
    A1,
    A0
  )
})


test_that("matrix unary sqrt with length(where) == nrow(matrix) and col_idx works", {
  A0 <- matrix(as.numeric(1:6), 2, 3)
  A1 <- duplicate(A0)
  
  ybr_sqrt(A1, where = c(F, T), cols = 1:2)
  
  A0[2] <- sqrt(A0[2])
  A0[4] <- sqrt(A0[4])
  
  expect_identical(
    A1,
    A0
  )
})




test_that("matrix unary sqrt with 'idx' and 'cols' works", {
  A0 <- matrix(as.numeric(1:6), 2, 3)
  A1 <- duplicate(A0)
  
  ybr_sqrt(A1, idx = c(1), cols = c(1, 3))
  
  A0[1] <- sqrt(A0[1])
  A0[5] <- sqrt(A0[5])
  
  expect_identical(
    A1,
    A0
  )
})

