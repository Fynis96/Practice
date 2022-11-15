const dummy = (blogs) => {
    return 1
}

const totalLikes = function (posts)  {
    if (posts.length === 0){
        return 0
    } else if(posts.length === 1)
    {
        return posts[0].likes
    } else if(posts.length >= 2) {
        const result = posts.map(({likes}) => likes)
        const total = result.reduce((p, c) => p + c, 0)
        return total
    }
}

const favoriteBlog = function (posts)  {
    if (posts.length === 0){
        return 0
    } else if(posts.length === 1)
    {
        return posts[0]
    } else if(posts.length >= 2) {
        let highest = 0
        let highestIndex = 0
        for (let i = 0; i < posts.length; i++)
        {
            if (posts[i].likes > highest)
            {
                highest = posts[i].likes
                highestIndex = i
            } 
        }
        return posts[highestIndex]
    }
}

const testInput = (str) => {
    return /.{3,}/.test(str)
}

module.exports = {
    dummy, totalLikes, favoriteBlog, testInput
}