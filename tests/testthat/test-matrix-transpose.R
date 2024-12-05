
test_that("matrix tranpose works", {
  
  m1 <- matrix(as.numeric(1:6), 2, 3)
  m2 <- matrix(as.numeric(1:6), 2, 3)
  br_mat_transpose(m1)

  expect_equal(
    m1,
    t(m2)
  )
  
})
