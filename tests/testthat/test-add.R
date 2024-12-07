
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
