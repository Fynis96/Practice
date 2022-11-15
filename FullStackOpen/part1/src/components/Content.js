import React from 'react'
import Part from './Part'
import Total from './Total'
const Content = (props) => {
    const createParts = () => {
        let arr = [];
        for (let i = 0; i < props.course.parts.length; i++)
        {
            arr.push(<Part key={i} partText={props.course.parts[i].name} partNum={props.course.parts[i].exercises}/>)
        }
        return arr
    }

    

    return (
        <div>
            {createParts()}
            <Total text={props.course.parts} />
        </div>
    )
  }
  
export default Content