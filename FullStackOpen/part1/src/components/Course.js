import React from 'react'
import Header from './Header'
import Content from './Content'

const Course = (props) => {
    return (
        <div>
            <Header text={props.courses} />
            <Content course={props.courses} />
        </div>
        )
  }
  
export default Course