


test_that("transform3d on matrix works", {

  tf <- tf3_new()
  tf3_add_translate(tf, x = 1, y = 2, z = 3)
  mat <- matrix(c(1, 2, 3, 4, 5, 6, 7, 8, 9), 3, 3)
  mat 
  tf2_apply(mat, tf)

  expect_equal(
    mat, 
    matrix(c(
      1 + 1, 4 + 2, 7 + 3,
      2 + 1, 5 + 2, 8 + 3,
      3 + 1, 6 + 2, 9 + 3
    ), 3, 3, byrow = TRUE)
  )
    
  
})


test_that("transform3d on df-to-matrix works", {
  
  tf <- tf3_new()
  tf3_add_translate(tf, x = 1, y = 2, z = 3)
  mat <- matrix(c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12), 4, 3)
  df <- as.data.frame(mat) |>
    setNames(c('x', 'y', 'z'))
  mat <- as.matrix(df)
  tf3_apply(mat, tf)
  
  expect_equal(
    unname(mat), 
    matrix(c(
      1 + 1, 5 + 2,  9 + 3,
      2 + 1, 6 + 2, 10 + 3,
      3 + 1, 7 + 2, 11 + 3,
      4 + 1, 8 + 2, 12 + 3
    ), 4, 3, byrow = TRUE)
  )
})


test_that("transform3d on data.frame works", {
  
  tf <- tf3_new()
  tf3_add_translate(tf, x = 1, y = 2, z = 3)
  mat <- matrix(c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12), 4, 3)
  df <- as.data.frame(mat) |>
    setNames(c('x', 'y', 'z'))
  tf3_apply(df, tf)
  
  expect_equal(df$x, c(1, 2, 3, 4) + 1)
  expect_equal(df$y, c(5, 6, 7, 8) + 2)
})
