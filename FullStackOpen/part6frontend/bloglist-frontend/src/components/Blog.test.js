import React from 'react'
import '@testing-library/jest-dom/extend-expect'
import { render } from '@testing-library/react'
import userEvent from '@testing-library/user-event'
import Blog from './Blog'

test('renders blog, but not likes and url by default', () => {
  const blog = {
    title: 'This is the title',
    author: 'This is the author',
    likes: 20,
    url: 'wtf.com'
  }

  const { container } = render(<Blog blog={blog} />)

  const title = container.querySelector('.title')

  expect(title).toBeDefined()

  const likes = container.querySelector('.likes')
  expect(likes).toBeNull()
})

test('information renders properly after toggle button is clicked', async () => {
  const userE = userEvent.setup()
  const blog = {
    title: 'This is the title',
    author: 'This is the author',
    likes: 20,
    url: 'wtf.com',
    user: { name: 'test' }
  }
  const user = {
    name: 'test'
  }

  const { container } = render(<Blog blog={blog} user={user} />)

  const toggle = container.querySelector('.toggle')

  await userE.click(toggle)
  const likes = container.querySelector('.likes')
  expect(likes).toBeDefined()

})

test('like button sends proper event handlers when clicked', async () => {
  const updateLike = jest.fn()
  const userE = userEvent.setup()
  const blog = {
    title: 'This is the title',
    author: 'This is the author',
    likes: 20,
    url: 'wtf.com',
    user: { name: 'test' }
  }
  const user = {
    name: 'test'
  }

  const { container } = render(<Blog blog={blog} user={user} updateLike={updateLike}/>)

  const toggle = container.querySelector('.toggle')
  await userE.click(toggle)
  const likes = container.querySelector('.likesbtn')
  await userE.click(likes)
  await userE.click(likes)

  expect(updateLike.mock.calls).toHaveLength(2)
})