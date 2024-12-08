


test_that("by-reference abs works", {
  
  x <- as.numeric(seq(-5, 5))
  br_abs(x)
  expect_equal(
    x,
    c(5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5)
  )
})



test_that("by-reference abs works with 'where'", {
  
  x <- as.numeric(seq(-5, 5))
  where <- c(1, 1, 0,0,0,0,0,0,0,0,0)
  br_abs(x, where)
  expect_equal(
    x,
    c(5, 4, -3, -2, -1, 0, 1, 2, 3, 4, 5)
  )
})
