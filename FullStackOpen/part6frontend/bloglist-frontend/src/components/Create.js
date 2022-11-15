import { useState } from 'react'

const Create = ({ createBlog }) => {
  const [title, setTitle] = useState('')
  const [author, setAuthor] = useState('')
  const [url, setUrl] = useState('')
  const handleTitleChange = (event) => {
    setTitle(event.target.value)
  }
  const handleAuthorChange = (event) => {
    setAuthor(event.target.value)
  }
  const handleURLChange = (event) => {
    setUrl(event.target.value)
  }

  const addBlog = (event) => {
    event.preventDefault()
    createBlog({
      title: title,
      author: author,
      url: url
    })
    setUrl('')
    setAuthor('')
    setTitle('')
  }

  return (
    <form onSubmit={addBlog}>
      <div>
            title: <input className='title' value={title} onChange={handleTitleChange} />
      </div>
      <div>
            author: <input className='author' value={author} onChange={handleAuthorChange} />
      </div>
      <div>
            url: <input className='url' value={url} onChange={handleURLChange} />
      </div>
      <div>
        <button className='submit' type="submit">add</button>
      </div>
    </form>
  )
}
export default Create