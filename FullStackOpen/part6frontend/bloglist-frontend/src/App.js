/* eslint-disable react-hooks/exhaustive-deps */
import { useState, useEffect, useRef } from 'react'
import Blog from './components/Blog'
import blogService from './services/blogs'
import loginService from './services/login'
import Notification from './components/Notification'
import Create from './components/Create'
import Togglable from './components/Togglable'

const App = () => {
  const [blogs, setBlogs] = useState([])
  const [errorMessage, setErrorMessage] = useState('some error happened...')
  const [username, setUsername] = useState('')
  const [password, setPassword] = useState('')
  const [user, setUser] = useState(null)
  const blogFormRef = useRef()

  useEffect(async () => {
    const blogs = await blogService.getAll()
    setBlogs( blogs )
    setErrorMessage(null)
  }, [])

  useEffect(() => {
    const loggedUserJSON = window.localStorage.getItem('loggedBlogappUser')
    if (loggedUserJSON) {
      const user = JSON.parse(loggedUserJSON)
      setUser(user)
      blogService.setToken(user.token)
    }
  }, [])

  const handleLogin = async (event) => {
    event.preventDefault()

    try {
      const user = await loginService.login({
        username, password,
      })

      window.localStorage.setItem(
        'loggedBlogappUser', JSON.stringify(user)
      )
      blogService.setToken(user.token)
      setUser(user)
      setUsername('')
      setPassword('')
    } catch (exception) {
      setErrorMessage('Wrong credentials')
      setTimeout(() => {
        setErrorMessage(null)
      }, 5000)
      console.log(exception)
    }
  }

  const loginForm = () => (
    <form onSubmit={handleLogin}>
      <div>
        username
        <input
          type="text"
          value={username}
          name="Username"
          onChange={({ target }) => setUsername(target.value)}
        />
      </div>
      <div>
        password
        <input
          type="password"
          value={password}
          name="Password"
          onChange={({ target }) => setPassword(target.value)}
        />
      </div>
      <button type="submit">login</button>
    </form>
  )
  const updateLike = async (blogId, blogObject) => {
    const returnedBlog = await blogService.update(blogId, blogObject)
    setBlogs(blogs.map(blog => blog.id !== blogId ? blog : returnedBlog))
  }


  const addBlog = async (blogObject) => {
    blogFormRef.current.toggleVisibility()
    const returnedBlog = await blogService.create(blogObject)
    setBlogs(blogs.concat(returnedBlog))
    setErrorMessage(
      `${returnedBlog.title} was successfully added`
    )
    setTimeout(() => {
      setErrorMessage(null)
    }, 5000)
  }

  const removeBlog = async (blogId) => {
    const blogTitle = blogs.filter(blog => (blog.id === blogId))
    if(window.confirm(`Are you sure you wish to delete ${blogTitle[0].title}`))
    {
      await blogService.remove(blogId)
      setBlogs(blogs.filter(blog => (blog.id !== blogId)))
    }
  }

  return (
    <div>
      <Notification message={errorMessage} />
      {user === null ?
        loginForm() :
        <div>
          <p>{user.name} logged-in</p><button onClick={() => {window.localStorage.removeItem('loggedBlogappUser'); setUser(null)}}>logout</button>
          <h2>blogs</h2>
          <Togglable buttonLabel='new blog' ref={blogFormRef}>
            <Create createBlog={addBlog} />
          </Togglable>
          {blogs.sort((a, b) => b.likes - a.likes).map(blog =>
            <Blog key={blog.id} blog={blog} updateLike={updateLike} user={user} removeBlog={removeBlog} />
          )}
        </div>
      }
    </div>
  )
}

export default App