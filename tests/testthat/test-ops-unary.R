


test_that("by-reference sqrt works", {
  
  x <- as.numeric(seq(0, 5))
  br_sqrt(x)
  expect_equal(
    x,
    sqrt(0:5)
  )
})



test_that("by-reference sqrt works with 'where'", {
  
  x <- as.numeric(seq(0, 5))
  where <- c(0, 0, 0, 0, 0, 1)
  br_sqrt(x, where = where)
  expect_equal(
    x,
    c(0, 1, 2, 3, 4, sqrt(5))
  )
})


test_that("by-reference sqrt works with 'where'", {
  
  x <- as.numeric(seq(0, 5))
  where <- c(0, 0, 1, 0, 0, 1)
  br_sqrt(x, where = where)
  expect_equal(
    x,
    c(0, 1, sqrt(2), 3, 4, sqrt(5))
  )
})




test_that("by-reference sqrt works with 'idx'", {
  
  x <- as.numeric(seq(0, 5))
  idx <- 4:6
  br_sqrt(x, idx = idx)
  expect_equal(
    x,
    c(0, 1, 2, sqrt(c(3, 4, 5)))
  )
})
