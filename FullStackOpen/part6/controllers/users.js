const bcrypt = require('bcrypt')
const usersRouter = require('express').Router()
const User = require('../models/user')
const helper = require('../utils/list_helper')


usersRouter.get('/', async (request, response) => {
  const users = await User
    .find({}).populate('blogs', { url: 1, title: 1, author: 1 })

  response.json(users)
})

usersRouter.post('/', async (request, response) => {
  const { username, name, password } = request.body
  if(helper.testInput(username) && helper.testInput(password)){
    const users = await User.find({})
    const usernames = users.map(u => u.username)
    if(!(usernames.includes(username)))
    {
      const saltRounds = 10
      const passwordHash = await bcrypt.hash(password, saltRounds)

      const user = new User({
        username,
        name,
        passwordHash,
      })

      const savedUser = await user.save()

      response.status(201).json(savedUser)
    }
    else {
      response.status(400).json({
        error: 'username must be unique'
      })
    }
  }
else {
  response.status(400).json({
    error: 'username or Password must be over 3 characters long'
  })
}
})

module.exports = usersRouter