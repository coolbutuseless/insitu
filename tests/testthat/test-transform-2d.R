


test_that("transform2d on matrix works", {

  tf <- tf2_new()
  tf2_add_translate(tf, x = 1, y = 2)
  mat <- matrix(c(1, 2, 3, 4, 5, 6), 3, 2)
  mat 
  tf2_apply(mat, tf)

  expect_equal(
    mat, 
    matrix(c(
      1 + 1, 4 + 2,
      2 + 1, 5 + 2,
      3 + 1, 6 + 2
    ), 3, 2, byrow = TRUE)
  )
    
  
})


test_that("transform2d on df-to-matrix works", {
  
  tf <- tf2_new()
  tf2_add_translate(tf, x = 1, y = 2)
  mat <- matrix(c(1, 2, 3, 4, 5, 6, 7, 8), 4, 2)
  df <- as.data.frame(mat) |>
    setNames(c('x', 'y'))
  mat <- as.matrix(df)
  tf2_apply(mat, tf)
  
  expect_equal(
    unname(mat), 
    matrix(c(
      1 + 1, 5 + 2,
      2 + 1, 6 + 2,
      3 + 1, 7 + 2,
      4 + 1, 8 + 2
    ), 4, 2, byrow = TRUE)
  )
})


test_that("transform2d on data.frame works", {
  
  tf <- tf2_new()
  tf2_add_translate(tf, x = 1, y = 2)
  mat <- matrix(c(1, 2, 3, 4, 5, 6, 7, 8), 4, 2)
  df <- as.data.frame(mat) |>
    setNames(c('x', 'y'))
  tf2_apply(df, tf)
  
  expect_equal(df$x, c(1, 2, 3, 4) + 1)
  expect_equal(df$y, c(5, 6, 7, 8) + 2)
})
