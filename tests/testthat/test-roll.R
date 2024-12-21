

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Rolling by 0 or by n * length should just return the original vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test_that("roll(0) works", {
  
  x <- c(1, 2, 3, 4, 5)
  
  br_roll(x, 0)
  expect_identical(x, c(1, 2, 3, 4, 5))
  
  br_roll(x, 5)
  expect_identical(x, c(1, 2, 3, 4, 5))
  
  br_roll(x, 10)
  expect_identical(x, c(1, 2, 3, 4, 5))
  
  br_roll(x, -5)
  expect_identical(x, c(1, 2, 3, 4, 5))
  
  br_roll(x, -10)
  expect_identical(x, c(1, 2, 3, 4, 5))
})


test_that("roll() works", {
  
  x <- c(1, 2, 3, 4, 5)
  br_roll(x, 1)
  expect_identical(x, c(5, 1, 2, 3, 4));
  
  x <- c(1, 2, 3, 4, 5)
  br_roll(x, 2)
  expect_identical(x, c(4, 5, 1, 2, 3));
  
  x <- c(1, 2, 3, 4, 5)
  br_roll(x, 3)
  expect_identical(x, c(3, 4, 5, 1, 2));
  
  x <- c(1, 2, 3, 4, 5)
  br_roll(x, 4)
  expect_identical(x, c(2, 3, 4, 5, 1));
  
  x <- c(1, 2, 3, 4, 5)
  br_roll(x, 5)
  expect_identical(x, c(1, 2, 3, 4, 5));
  
  x <- c(1, 2, 3, 4, 5)
  br_roll(x, 6)
  expect_identical(x, c(5, 1, 2, 3, 4));
  
  x <- c(1, 2, 3, 4, 5)
  br_roll(x, -1)
  expect_identical(x, c(2, 3, 4, 5, 1));
  
  
})