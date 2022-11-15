const listHelper = require('../utils/list_helper')

const listWithOneBlog = [
    {
      _id: '5a422aa71b54a676234d17f8',
      title: 'Go To Statement Considered Harmful',
      author: 'Edsger W. Dijkstra',
      url: 'http://www.u.arizona.edu/~rubinson/copyright_violations/Go_To_Considered_Harmful.html',
      likes: 5,
      __v: 0
    }
  ]
  const listWithMultipleBlogs = [
      {
          _id: '5a422aa71b54a676234d17f8',
          title: 'Go To Statement Considered Harmful',
          author: 'Edsger W. Dijkstra',
          url: 'http://www.u.arizona.edu/~rubinson/copyright_violations/Go_To_Considered_Harmful.html',
          likes: 5,
          __v: 0
      },
      {
          _id: '5443223f125',
          title: 'Something',
          author: 'someone',
          url: 'http://www.u.arizona.edu/~rubinson/copyright_violations/Go_To_Considered_Harmful.html',
          likes: 22,
          __v: 0
      },
      {
          _id: '54432241241143f125',
          title: 'Something onece more',
          author: 'someone',
          url: 'http://www.u.arizona.edu/~rubinson/copyright_violations/Go_To_Considered_Harmful.html',
          likes: 44,
          __v: 0
      }
  ]
  const emptyList = []

describe('dummy function', () => {
    test('dummy returns one', () => {
        const blogs = []

        const result = listHelper.dummy(blogs)
        expect(result).toBe(1)
    })
})
describe('total likes', () => {
    
  
    test('when list has only one blog, equals the likes of that', () => {
      const result = listHelper.totalLikes(listWithOneBlog)
      expect(result).toBe(5)
    })

    test('when list has multiple blogs, add the likes together', () => {
        const result = listHelper.totalLikes(listWithMultipleBlogs)
        expect(result).toBe(71)
      })

    test('when list is empty, return 0', () => {
    const result = listHelper.totalLikes(emptyList)
    expect(result).toBe(0)
    })
  })

  describe('favoriteBlogs', () => {

      test('when list has only one blog, equals the likes of that', () => {
        const result = listHelper.favoriteBlog(listWithOneBlog)
        expect(result).toEqual(listWithOneBlog[0])
      })
  
      test('when list has multiple blogs, add the likes together', () => {
          const result = listHelper.favoriteBlog(listWithMultipleBlogs)
          expect(result).toEqual(listWithMultipleBlogs[2])
        })
  
      test('when list is empty, return 0', () => {
      const result = listHelper.favoriteBlog(emptyList)
      expect(result).toBe(0)
      })
  })