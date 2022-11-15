const blogRouter = require('express').Router()
const Blog = require('../models/blog')
const { userExtractor, tokenExtractor } = require('../utils/middleware')


blogRouter.get('/', async (request, response) => {
    const blogs = await Blog
        .find({}).populate('user', { username: 1, name: 1 })
    
    response.json(blogs)
})

blogRouter.get('/:id', async (request, response) => {
    const blog = await Blog.findById(request.params.id)
    if (blog) {
      response.json(blog)
    } else {
      response.status(404).end()
    }
  })

blogRouter.post('/', userExtractor, async (request, response) => {
    const body = request.body
    const user = request.user

    const blog = await new Blog({
        title: body.title,
        author: body.author,
        url: body.url,
        likes: body.likes,
        user: user._id
    })

    if (!blog.title || !blog.author) {
        response.status(400).end()
    }
    else {
    const savedBlog = await blog.save()
    user.blogs = user.blogs.concat(savedBlog._id)
    await user.save()

    response.status(201).json(savedBlog)
    }
})

blogRouter.delete('/:id', userExtractor, async (request, response) => {
    const user = await request.user
    const blogToDelete = await Blog.findById(request.params.id).populate('user', { id: 1 })
    if (blogToDelete.user.toString() === user.id.toString()){
        await Blog.findByIdAndRemove(request.params.id)
        response.status(204).end()
    }
    else if(blogToDelete.user._id.toString() === user.id.toString()){
        await Blog.findByIdAndRemove(request.params.id)
        response.status(204).end()
    }else{
        return response.status(401).json({ error: 'token missing or invalid' })
    }
})

blogRouter.put('/:id', async (request, response) => {
    const body = request.body

    const blog = {
        title: body.title,
        author: body.author,
        url: body.url,
        likes: body.likes,
        user: body.user
    }

    const updatedNote = await Blog.findByIdAndUpdate(request.params.id, blog, { new: true}).populate('user', { name: 1 })
    response.status(201).json(updatedNote)
})

module.exports = blogRouter