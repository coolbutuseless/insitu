

test_that("br_mat_normalise3() works", {
  
  set.seed(1)
  N <- 100
  
  x <- runif(N)
  y <- runif(N)
  z <- runif(N)
  
  len <- sqrt(x * x + y * y + z * z)
  x1 <- x / len
  y1 <- y / len
  z1 <- z / len
  len1 <- sqrt(x1 * x1 + y1 * y1 + z1 * z1)
  expect_true(all.equal(len1, rep(1, N)))

  mat <- cbind(x, y, z)
  br_mat_normalise3(mat)
  
  x2 <- mat[,1]
  y2 <- mat[,2]
  z2 <- mat[,3]
  
  len2 <- sqrt(x2 * x2 + y2 * y2 + z2 * z2)
  expect_true(all.equal(len2, rep(1, N)))
  
  
  expect_equal(x2, x1)
  expect_equal(y2, y1)
  expect_equal(z2, z1)
      
})





test_that("br_mat_normalise3() works", {
  
  set.seed(1)
  N <- 100
  
  x <- runif(N)
  y <- runif(N)
  
  len <- sqrt(x * x + y * y)
  x1 <- x / len
  y1 <- y / len
  len1 <- sqrt(x1 * x1 + y1 * y1)
  expect_true(all.equal(len1, rep(1, N)))
  
  mat <- cbind(x, y)
  br_mat_normalise2(mat)
  
  x2 <- mat[,1]
  y2 <- mat[,2]
  
  len2 <- sqrt(x2 * x2 + y2 * y2)
  expect_true(all.equal(len2, rep(1, N)))
  
  
  expect_equal(x2, x1)
  expect_equal(y2, y1)
  
})
