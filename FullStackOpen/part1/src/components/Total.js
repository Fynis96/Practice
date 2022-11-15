import React from 'react'

const Total = (props) => {
    const total = props.text.reduce((p, c) => p + c.exercises, 0)
    
    return (
      <p><b>total of {total} exercises</b></p>
    )
  }
  
export default Total