
test_that("by reference addition vector-vector", {

  x <- as.numeric(1:10)
  y <- as.numeric(1:10)
  
  br_add(x, y)
  expect_equal(
    x,
    seq(2, 20, 2)
  )
  
})


test_that("by reference addition vector-scalar", {
  
  x <- as.numeric(1:10)
  y <- 2.5
  
  br_add(x, y)
  expect_equal(
    x,
    seq(1:10) + 2.5
  )
  
})


test_that("by reference addition vector-vector with 'where' conditional", {
  
  x <- as.numeric(1:10)
  y <- as.numeric(1:10)
  where <- c(1, 1, 1, 1, 1, 0, 0, 0, 0, 0)
  
  br_add(x, y, where = where)
  expect_equal(
    x,
    c(seq(2, 10, 2), 6, 7, 8, 9, 10)
  )
  
})


test_that("by reference addition vector-scalar with 'where' conditional", {
  
  x <- as.numeric(1:10)
  y <- 2.5
  where <- c(1, 1, 1, 1, 1, 0, 0, 0, 0, 0)
  
  br_add(x, y, where = where)
  expect_equal(
    x,
    c((1:5) + 2.5, 6, 7, 8, 9, 10)
  )
  
})

