import React from 'react'
import '@testing-library/jest-dom/extend-expect'
import { render } from '@testing-library/react'
import userEvent from '@testing-library/user-event'
import Create from './Create'

test('form properly creates a new blog to be rendered', async () => {
  const createBlog = jest.fn()
  const userE = userEvent.setup()

  const { container } = render(<Create createBlog={createBlog} />)

  const title = container.querySelector('.title')
  const author = container.querySelector('.author')
  const url = container.querySelector('.url')
  const btn = container.querySelector('.submit')

  await userE.type(title, 'This is a title')
  await userE.type(author, 'This is the Author')
  await userE.type(url, 'url.com')
  await userE.click(btn)

  expect(createBlog.mock.calls).toHaveLength(1)
})