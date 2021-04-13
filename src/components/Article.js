import React from 'react';

function Article(props) {
  if (props.article.content != null) {
    return (
        <article>
            <a href={props.article.url} target="_blank" rel="noreferrer">
                <h3>{props.article.title}</h3>
            </a>
        </article>
    )
  }
  return null;
}

export default Article;