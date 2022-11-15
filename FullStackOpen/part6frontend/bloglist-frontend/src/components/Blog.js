import { useState } from 'react'

const Blog = ({ blog, updateLike, user, removeBlog }) => {
  const [toggled, setToggle] = useState(true)
  const [likes, setLikes] = useState(blog.likes)

  const blogStyle = {
    paddingTop: 10,
    paddingLeft: 2,
    border: 'solid',
    borderWidth: 1,
    marginBottom: 5
  }
  const upLike = () => {
    let newLike = likes + 1
    updateLike(blog.id, {
      user: blog.user.id,
      likes: newLike,
      author: blog.author,
      title: blog.title,
      url: blog.url
    })
    setLikes(newLike)
  }



  return (
    <div style={blogStyle}>
      {toggled ?
        <div>
          <b>{blog.title}</b> - {blog.author}<button className='toggle' onClick={() => {setToggle(!toggled)}}>view</button>
        </div>
        :
        <div>
          <ul style={{ listStyleType: 'none', padding: 0, margin: 0 }}>
            <li className="content"><b>{blog.title}</b> - {blog.author}<button onClick={() => {setToggle(!toggled)}}>hide</button></li>
            <li className="url">{blog.url}</li>
            <li className="likes">likes {likes} <button className="likesbtn" onClick={() => {upLike()}}>like</button></li>
            <li className="user">{blog.user.name}</li> {user.name !== blog.user.name ? '' : <button onClick={() => {removeBlog(blog.id)}}>remove</button>
            }
          </ul>
        </div>
      }
    </div>
  )}

export default Blog