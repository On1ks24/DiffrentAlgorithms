using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3
{
    public class Node<T>
    {
        public T Content { get; set; }
        public Node<T> Next { get; set; }

        public Node(T content)
        {
            Content = content;
            Next = null;
        }
    }

    public class MyQueue<T>
    {
        private Node<T> First;
        private Node<T> Last;
        private int count;

        public MyQueue()
        {
            First = null;
            Last = null;
            count = 0;
        }

        public int Count
        {
            get { return count; }
        }

        public bool IsEmpty()
        {
            return First == null;
        }

        public void Enqueue(T data)
        {
            Node<T> newNode = new Node<T>(data);

            if (IsEmpty())
            {
                First = newNode;
            }
            else
            {
                Last.Next = newNode;
            }

            Last = newNode;
            count++;
        }

        public T Dequeue()
        {
            if (IsEmpty())
            {
                throw new InvalidOperationException("Queue is empty");
            }

            T data = First.Content;
            First = First.Next;
            count--;

            if (First == null)
            {
                Last = null;
            }

            return data;
        }
    }
}
