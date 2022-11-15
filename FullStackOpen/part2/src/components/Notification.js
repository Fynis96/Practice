const Notification = ({ message }) => {
  if (message === null) {
    return <div></div>
  }

  return (
    <div className='error'>
      {message}
    </div>
  )
}

export default Notification